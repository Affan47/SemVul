setImagePath(const QString &svgFilePath)
{

    if (FrameSvg *frame = qobject_cast<FrameSvg *>(this)) {
        frame->setImagePath(svgFilePath);
        return;
    }

    d->setImagePath(svgFilePath);

    emit repaintNeeded();
}
