createContainer()
    {
        OverlayContainer* container = (OverlayContainer*)
            OverlayManager::getSingleton().createOverlayElement(
                "BorderPanel", "profiler");
        container->setMetricsMode(GMM_PIXELS);
        container->setMaterialName("Core/StatsBlockCenter");
        container->setHeight(mGuiHeight);
        container->setWidth(mGuiWidth * 2 + 15);
        container->setParameter("border_size", "1 1 1 1");
        container->setParameter("border_material", "Core/StatsBlockBorder");
        container->setParameter("border_topleft_uv", "0.0000 1.0000 0.0039 0.9961");
        container->setParameter("border_top_uv", "0.0039 1.0000 0.9961 0.9961");
        container->setParameter("border_topright_uv", "0.9961 1.0000 1.0000 0.9961");
        container->setParameter("border_left_uv","0.0000 0.9961 0.0039 0.0039");
        container->setParameter("border_right_uv","0.9961 0.9961 1.0000 0.0039");
        container->setParameter("border_bottomleft_uv","0.0000 0.0039 0.0039 0.0000");
        container->setParameter("border_bottom_uv","0.0039 0.0039 0.9961 0.0000");
        container->setParameter("border_bottomright_uv","0.9961 0.0039 1.0000 0.0000");
        container->setLeft(5);
        container->setTop(5);

        return container;
    }
