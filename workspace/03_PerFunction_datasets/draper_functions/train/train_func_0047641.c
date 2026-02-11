_resolveComponents(LodConfig& lodConfig,
                                          LodCollapseCostPtr& cost,
                                          LodDataPtr& data,
                                          LodInputProviderPtr& input,
                                          LodOutputProviderPtr& output,
                                          LodCollapserPtr& collapser)
{
    if(cost.isNull()) {
        cost = LodCollapseCostPtr(new LodCollapseCostCurvature);
        if(lodConfig.advanced.outsideWeight != 0) {
            cost =
                LodCollapseCostPtr(new LodCollapseCostOutside(cost, lodConfig.advanced.outsideWeight,
                                                              lodConfig.advanced.outsideWalkAngle));
        }
        if(!lodConfig.advanced.profile.empty()) {
            cost = LodCollapseCostPtr(new LodCollapseCostProfiler(lodConfig.advanced.profile, cost));
        }

    }
    if(data.isNull()) {
        data = LodDataPtr(new LodData());
    }
    if(collapser.isNull()) {
        collapser = LodCollapserPtr(new LodCollapser());
    }
    if(lodConfig.advanced.useBackgroundQueue) {
        if(input.isNull()) {
            input = LodInputProviderPtr(new LodInputProviderBuffer(lodConfig.mesh));
        }
        if(output.isNull()) {
            if(lodConfig.advanced.useCompression) {
                output = LodOutputProviderPtr(new LodOutputProviderCompressedBuffer(lodConfig.mesh));
            } else {
                output = LodOutputProviderPtr(new LodOutputProviderBuffer(lodConfig.mesh));
            }
        }
    } else {
        if(input.isNull()) {
            input = LodInputProviderPtr(new LodInputProviderMesh(lodConfig.mesh));
        }
        if(output.isNull()) {
            if(lodConfig.advanced.useCompression) {
                output = LodOutputProviderPtr(new LodOutputProviderCompressedMesh(lodConfig.mesh));
            } else {
                output = LodOutputProviderPtr(new LodOutputProviderMesh(lodConfig.mesh));
            }
        }
    }
}
