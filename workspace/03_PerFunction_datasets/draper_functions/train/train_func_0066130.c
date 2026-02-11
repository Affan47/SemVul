createInstance(ScriptCompiler* compiler,
                                                       PropertyAbstractNode* prop, Pass* pass, SGScriptTranslator* translator)
    {
        if (prop->name == "triplanarTexturing")
        {
            if (prop->values.size() == 6)
            {
                SubRenderState* subRenderState = createOrRetrieveInstance(translator);
                TriplanarTexturing* tpSubRenderState = static_cast<TriplanarTexturing*>(subRenderState);

                AbstractNodeList::const_iterator it = prop->values.begin();
                float parameters[3];
                if (false == SGScriptTranslator::getFloat(*it, parameters))
                {
                    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
                    return NULL;
                }
                ++it;
                if (false == SGScriptTranslator::getFloat(*it, parameters + 1))
                {
                    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
                    return NULL;
                }
                ++it;
                if (false == SGScriptTranslator::getFloat(*it, parameters + 2))
                {
                    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
                    return NULL;
                }
                Vector3 vParameters(parameters[0], parameters[1], parameters[2]);
                tpSubRenderState->setParameters(vParameters);

                String textureNameFromX, textureNameFromY, textureNameFromZ;
                ++it;
                if (false == SGScriptTranslator::getString(*it, &textureNameFromX))
                {
                    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
                    return NULL;
                }
                ++it;
                if (false == SGScriptTranslator::getString(*it, &textureNameFromY))
                {
                    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
                    return NULL;
                }
                ++it;
                if (false == SGScriptTranslator::getString(*it, &textureNameFromZ))
                {
                    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
                    return NULL;
                }
                tpSubRenderState->setTextureNames(textureNameFromX, textureNameFromY, textureNameFromZ);

                return subRenderState;
            }
            else
            {
                compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
            }
        }
        return NULL;
    }
