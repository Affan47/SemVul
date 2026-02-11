Input()
{

    ByteAlignInput();

    m_cparams.SetZeroTransform(false);

    if (m_fparams.PicSort().IsInter())
        m_cparams.SetZeroTransform(ReadBool());

    if (m_cparams.ZeroTransform())
        return;


    m_cparams.SetTransformFilter(ReadUint());


     m_cparams.SetTransformDepth(ReadUint());


    m_cparams.SetSpatialPartition(ReadBool());

    if (m_cparams.SpatialPartition())
    {

        for (unsigned int i = 0; i <= m_cparams.TransformDepth(); ++i)
        {

            unsigned int hblocks = ReadUint();

            unsigned int vblocks = ReadUint();
            m_cparams.SetCodeBlocks(i, hblocks, vblocks);
        }

        m_cparams.SetCodeBlockMode(ReadUint());
    }

    ByteAlignInput();
}
