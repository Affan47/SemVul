ImpliedPanning(const MediaAudioChannelDef& inDef)
{
    tVal retVal;

    t4Val vecToSound = m_listenerPost.AngPos().Conjugate().RotatedVector(inDef.Position() - m_listenerPost.Pos());
    tVal distToSound = vecToSound.Magnitude();

    if (distToSound < 0.1)
    {
        retVal = 0.0;
    }
    else
    {
        retVal = vecToSound.X() / distToSound;
    }
    return retVal;
}
