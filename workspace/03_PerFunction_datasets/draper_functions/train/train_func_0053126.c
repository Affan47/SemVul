colorfieldChanged()
{
    SpecialFields sp;
    int index = fieldChooser->currentIndex();
    if (index >=0) parent->colorfield = sp.internalName(fieldChooser->itemText(fieldChooser->currentIndex()));
}
