paint_constraints(AW_device *device) {
    double minS = helix_info->minSize();
    double maxS = helix_info->maxSize();

    if (minS>0 || maxS>0) {
        const Position& startP = startAttachPoint();
        const Position& endP   = endAttachPoint();

        bool drawMidLine = minS>0 && maxS>0;
        Position minP = startP + Vector(startP, endP) * (drawMidLine ? minS/maxS : 0.5);

        get_root()->paintAnnotation(device, SEC_GC_DEFAULT,
                                    minP, startP, endP,
                                    get_root()->display_params().distance_between_strands*2,
                                    GBS_global_string("%.1f-%.1f", minS, maxS),
                                    drawMidLine, true, true,
                                    self(), startAttachAbspos());
    }
}
