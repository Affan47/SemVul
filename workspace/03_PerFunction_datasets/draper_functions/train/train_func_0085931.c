createFadeAnim(const QList<KBlocksSvgItem*> & items, int duration, QTimeLine::Direction direction)
{
    if (mpAnimFade)
    {
        return false;
    }

    mpAnimFade = new KBlocksAnimFade(items, duration, direction);

    if (direction == QTimeLine::Forward)
    {
        connect(mpAnimFade, SIGNAL(animationFinished()), this, SLOT(endFadeInAnim()));
    }
    else
    {
        connect(mpAnimFade, SIGNAL(animationFinished()), this, SLOT(endFadeOutAnim()));
    }

    return true;
}
