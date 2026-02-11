draw() const
{

    d_renderSystem.setScissorTest(true, d_clipRect.d_left, d_clipRect.d_top,
                                  d_clipRect.d_right, d_clipRect.d_bottom);

    if (!d_sync)
        syncHardwareBuffer();

    if (!d_matrixValid)
        updateMatrix();

    d_renderSystem._setWorldMatrix(d_matrix);

    d_owner.setupRenderingBlendMode(d_blendMode);

    const int pass_count = d_effect ? d_effect->getPassCount() : 1;
    for (int pass = 0; pass < pass_count; ++pass)
    {

        if (d_effect)
            d_effect->performPreRenderFunctions(pass);


        size_t pos = 0;
        BatchList::const_iterator i = d_batches.begin();
        for ( ; i != d_batches.end(); ++i)
        {
            d_renderOp.vertexData->vertexStart = pos;
            d_renderOp.vertexData->vertexCount = (*i).second;
            d_renderSystem._setTexture(0, true, (*i).first);
            initialiseTextureStates();
            d_renderSystem._render(d_renderOp);
            pos += (*i).second;
        }
    }


    if (d_effect)
        d_effect->performPostRenderFunctions();
}
