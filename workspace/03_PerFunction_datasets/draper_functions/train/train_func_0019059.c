slotEditVarRemove()
{
    if(!game().isMainline())
    {
        game().removeVariation(game().variationNumber());
        slotGameChanged();
    }
}
