slotFlipVertically()
{
    QList<PictureContent *> pictures = projectList<QGraphicsItem, PictureContent>(selectedItems());
    foreach (PictureContent * picture, pictures)
        picture->addEffect(PictureEffect::FlipV);
}
