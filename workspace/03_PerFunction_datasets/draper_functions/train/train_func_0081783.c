_k_slotIconSizeChanged(int _value)
{
    int maxSize = KIconLoader::SizeEnormous - KIconLoader::SizeSmall;
    int value = (maxSize * _value / 100) + KIconLoader::SizeSmall;
    switch (value) {
        case KIconLoader::SizeSmall:
        case KIconLoader::SizeSmallMedium:
        case KIconLoader::SizeMedium:
        case KIconLoader::SizeLarge:
        case KIconLoader::SizeHuge:
        case KIconLoader::SizeEnormous:
            iconSizeSlider->setToolTip(i18n("Icon size: %1 pixels (standard size)", value));
            break;
        default:
            iconSizeSlider->setToolTip(i18n("Icon size: %1 pixels", value));
            break;
    }
}
