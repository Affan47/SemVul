addPath<agg::rasterizer_scanline_aa<> >(agg::rasterizer_scanline_aa<>& ras,
                                                      const agg::trans_affine& tr,
                                                      const AST::CommandInfo& attr)
{
    apply(attr, tr, 1.0);

    if (attr.mFlags & AST::CF_FILL) {
        ras.add_path(curvedTrans, attr.mIndex);
    } else {
        if (attr.mFlags & AST::CF_ISO_WIDTH) {
            ras.add_path(curvedTransStroked, attr.mIndex);
        } else {
            ras.add_path(curvedStrokedTrans, attr.mIndex);
        }
    }
}
