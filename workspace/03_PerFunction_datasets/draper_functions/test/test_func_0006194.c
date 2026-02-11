v4l2_device_register_subdev_nodes(struct v4l2_device *v4l2_dev)
{
	struct video_device *vdev;
	struct v4l2_subdev *sd;
	int err;


	list_for_each_entry(sd, &v4l2_dev->subdevs, list) {
		if (!(sd->flags & V4L2_SUBDEV_FL_HAS_DEVNODE))
			continue;

		vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
		if (!vdev) {
			err = -ENOMEM;
			goto clean_up;
		}

		video_set_drvdata(vdev, sd);
		strlcpy(vdev->name, sd->name, sizeof(vdev->name));
		vdev->v4l2_dev = v4l2_dev;
		vdev->fops = &v4l2_subdev_fops;
		vdev->release = v4l2_device_release_subdev_node;
		vdev->ctrl_handler = sd->ctrl_handler;
		err = __video_register_device(vdev, VFL_TYPE_SUBDEV, -1, 1,
					      sd->owner);
		if (err < 0) {
			kfree(vdev);
			goto clean_up;
		}
#if defined(CONFIG_MEDIA_CONTROLLER)
		sd->entity.info.dev.major = VIDEO_MAJOR;
		sd->entity.info.dev.minor = vdev->minor;
#endif
		sd->devnode = vdev;
	}
	return 0;

clean_up:
	list_for_each_entry(sd, &v4l2_dev->subdevs, list) {
		if (!sd->devnode)
			break;
		video_unregister_device(sd->devnode);
	}

	return err;
}
