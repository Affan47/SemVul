deriveTextureRenderTargetOptions(
    const String& texname, bool *hwGammaWrite, uint *fsaa, String* fsaaHint)
{


    bool renderingScene = false;

    CompositionTechnique::TargetPassIterator it = mTechnique->getTargetPassIterator();
    while (it.hasMoreElements())
    {
        CompositionTargetPass* tp = it.getNext();
        if (tp->getOutputName() == texname)
        {
            if (tp->getInputMode() == CompositionTargetPass::IM_PREVIOUS)
            {


                CompositorChain::InstanceIterator instit = mChain->getCompositors();
                renderingScene = true;
                while(instit.hasMoreElements())
                {
                    CompositorInstance* inst = instit.getNext();
                    if (inst == this)
                        break;
                    else if (inst->getEnabled())
                    {


                        renderingScene = false;
                    }
                }
                if (renderingScene)
                    break;
            }
            else
            {

                CompositionTargetPass::PassIterator pit = tp->getPassIterator();
                while(pit.hasMoreElements())
                {
                    CompositionPass* pass = pit.getNext();
                    if (pass->getType() == CompositionPass::PT_RENDERSCENE)
                    {
                        renderingScene = true;
                        break;
                    }
                }
            }

        }
    }

    if (renderingScene)
    {

        RenderTarget* target = mChain->getViewport()->getTarget();
        *hwGammaWrite = target->isHardwareGammaEnabled();
        *fsaa = target->getFSAA();
        *fsaaHint = target->getFSAAHint();
    }
    else
    {
        *hwGammaWrite = false;
        *fsaa = 0;
        *fsaaHint = BLANKSTRING;
    }

}
