sliderMoved(Slider* slider)
{
    if (slider->getName() == REFLECTIONMAP_POWER_SLIDER)
    {
        Real reflectionPower = slider->getValue();

        if (mReflectionMapSubRS != NULL)
        {
            ShaderExReflectionMap* reflectionMapSubRS = static_cast<ShaderExReflectionMap*>(mReflectionMapSubRS);


            reflectionMapSubRS->setReflectionPower(reflectionPower);


            RTShader::SubRenderStateSet instanceSet = mReflectionMapSubRS->getAccessor()->getSubRenderStateInstanceSet();
            RTShader::SubRenderStateSetIterator it = instanceSet.begin();
            RTShader::SubRenderStateSetIterator itEnd = instanceSet.end();

            for (; it != itEnd; ++it)
            {
                ShaderExReflectionMap* reflectionMapSubRSInstance = static_cast<ShaderExReflectionMap*>(*it);

                reflectionMapSubRSInstance->setReflectionPower(reflectionPower);
            }
        }
    }

    if (slider->getName() == MODIFIER_VALUE_SLIDER)
    {
        if (mLayeredBlendingEntity != NULL)
        {
            Ogre::Real val = mModifierValueSlider->getValue();
            mLayeredBlendingEntity->getSubEntity(0)->setCustomParameter(2, Vector4(val,val,val,0));
        }
    }
}
