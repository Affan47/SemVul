gd_loadimage_gd(GVJ_t * job, usershape_t *us, boxf b, boolean filled)
{
    gdImagePtr im2, im = (gdImagePtr) job->context;

    if ((im2 = gd_loadimage(job, us))) {
        if (job->rotation)
	    im2 = gd_rotateimage(im2, job->rotation);
        gdImageCopyResized(im, im2, ROUND(b.LL.x), ROUND(b.LL.y), 0, 0,
                ROUND(b.UR.x - b.LL.x), ROUND(b.UR.y - b.LL.y), im2->sx, im2->sy);
    }
}
