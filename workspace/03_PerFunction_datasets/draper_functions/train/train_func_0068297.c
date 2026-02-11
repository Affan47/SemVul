updateLightList(const Camera* i_pCamera, const LightList& i_LightList)
{
    if (isActive())
    {
        arrangeLightsInSegmentedLists(i_pCamera, i_LightList);
        updateTextureFromSegmentedLists(i_pCamera);
    }
}
