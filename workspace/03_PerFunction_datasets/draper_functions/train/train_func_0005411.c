pclxl_setlinejoin(gx_device_vector * vdev, gs_line_join join)
{
    stream *s = gdev_vector_stream(vdev);

    if ((join < 0) || (join > 3)) {
        emprintf1(vdev->memory,
                  "Igoring invalid linejoin enumerator %d\n",
                  join);
        return 0;
    }

    px_put_ub(s, (byte) join);
    px_put_ac(s, pxaLineJoinStyle, pxtSetLineJoin);
    return 0;
}
