malloc_bufs_check(void)
{
    OOPS_ON(malloc_video_bufs > 0, "malloc_video_bufs is %d (expected 0)",
	    malloc_video_bufs);
    OOPS_ON(malloc_audio_bufs > 0, "malloc_audio_bufs is %d (expected 0)",
	    malloc_audio_bufs);
}
