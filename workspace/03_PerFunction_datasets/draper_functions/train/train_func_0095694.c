em28xx_ctrl_notify(struct v4l2_ctrl *ctrl, void *priv)
{
	struct em28xx *dev = priv;


	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		dev->mute = ctrl->val;
		em28xx_audio_analog_set(dev);
		break;
	case V4L2_CID_AUDIO_VOLUME:
		dev->volume = ctrl->val;
		em28xx_audio_analog_set(dev);
		break;
	}
}
