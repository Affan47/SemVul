createOrRetrieveSubRenderState(SGScriptTranslator* translator)
{
    LayeredBlending* layeredBlendState;

    SubRenderState* subState = translator->getGeneratedSubRenderState(getType());
    if (subState != NULL)
    {
        layeredBlendState = static_cast<LayeredBlending*>(subState);
    }
    else
    {
        SubRenderState* subRenderState = createOrRetrieveInstance(translator);
        layeredBlendState = static_cast<LayeredBlending*>(subRenderState);
    }
    return layeredBlendState;
}
