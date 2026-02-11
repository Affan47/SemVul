rcRasterizeTriangles(rcContext* ctx, const float* verts, const unsigned char* areas, const int nt,
                          rcHeightfield& solid, const int flagMergeThr)
{
    rcAssert(ctx);

    ctx->startTimer(RC_TIMER_RASTERIZE_TRIANGLES);

    const float ics = 1.0f/solid.cs;
    const float ich = 1.0f/solid.ch;

    for (int i = 0; i < nt; ++i)
    {
        const float* v0 = &verts[(i*3+0)*3];
        const float* v1 = &verts[(i*3+1)*3];
        const float* v2 = &verts[(i*3+2)*3];

        rasterizeTri(v0, v1, v2, areas[i], solid, solid.bmin, solid.bmax, solid.cs, ics, ich, flagMergeThr);
    }

    ctx->stopTimer(RC_TIMER_RASTERIZE_TRIANGLES);
}
