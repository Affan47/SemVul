setup()
{
  CRITICAL(anim = animation_load(path_to_data("balloon-float.png"),
			       1,1,33));
  CRITICAL(hit_anim = animation_load(path_to_data("balloon-bounce.png"),
			       1,32,33));
  CRITICAL(deflate_anim =
	   animation_load(path_to_data("balloon-deflate.png"),1,32,30));
  animation_last_frame(hit_anim)->trigger = frame_trigger;
  animation_last_frame(deflate_anim)->trigger = killme;
  return 0;
}
