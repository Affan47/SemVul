radeonRenderStart( struct gl_context *ctx )
{
    r100ContextPtr rmesa = R100_CONTEXT( ctx );

    radeonSetVertexFormat( ctx );

    if (rmesa->radeon.dma.flush != 0 &&
            rmesa->radeon.dma.flush != rcommon_flush_last_swtcl_prim)
        rmesa->radeon.dma.flush( ctx );
}
