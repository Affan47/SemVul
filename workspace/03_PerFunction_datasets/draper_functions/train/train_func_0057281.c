dc1394_capture_is_frame_corrupt (dc1394camera_t * camera,
        dc1394video_frame_t * frame)
{
    dc1394camera_priv_t * cpriv = DC1394_CAMERA_PRIV (camera);
    if (!frame)
        return DC1394_TRUE;
    const platform_dispatch_t * d = cpriv->platform->dispatch;
    if (!d->capture_is_frame_corrupt)
        return DC1394_FALSE;
    return d->capture_is_frame_corrupt (cpriv->pcam, frame);
}
