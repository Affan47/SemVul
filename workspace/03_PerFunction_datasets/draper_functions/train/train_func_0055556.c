Open(const char *path)
{
	input_plugin *best_plugin;
	int frame_size = 0;

	Close();

	if (path == NULL || strlen(path) == 0) {
		alsaplayer_error("No path supplied");
		return false;
	}
	if ((best_plugin = GetPlayer(path)) == NULL) {
		alsaplayer_error("No suitable plugin found for \"%s\"", path);
		return false;
	}
	Lock();

	the_object->local_data = NULL;

	if (best_plugin->open(the_object, path)) {
		if ((frame_size = best_plugin->frame_size(the_object)) > BUF_SIZE) {
			alsaplayer_error("CRITICAL ERROR: this plugin advertised a buffer size\n"
					 "larger than %d bytes. This is not supported by AlsaPlayer!\n"
					 "Contact the author to fix this problem.\n"
					 "TECHNICAL: A possible solution is to divide the frame size\n"
					 "in 2 and double the number of effective frames. This can be\n"
					 "handled relatively easily in the plugin (hopefully).\n\n"
					 "We will retreat, as chaos and despair await us on\n"
					 "this chosen path........................................", BUF_SIZE);
			best_plugin->close(the_object);
			Unlock();
			return false;
		} else {
			if (!frame_size) {
					alsaplayer_error("No framesize");
					best_plugin->close(the_object);
					Unlock();
					return false;
			}

		}
	} else {
		best_plugin->close(the_object);
		Unlock();
		return false;
	}

	the_object->ready = 1;
	plugin = best_plugin;

	frames_in_buffer = read_buf->buf->GetBufferSizeBytes(plugin->frame_size(the_object)) / plugin->frame_size(the_object);

	Unlock();

	return true;
}
