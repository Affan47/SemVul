extract_sanitize_args(ExtractArgs *args)
{
    args->xpos = CLAMP(args->xpos, 0, 100);
    args->ypos = CLAMP(args->ypos, 0, 100);
    args->zpos = CLAMP(args->zpos, 0, 100);
    args->size = CLAMP(args->size, 1, 100);
    args->zscale = CLAMP(args->zscale, 1, 100);
    args->opacity = CLAMP(args->opacity, 1, 100);
    args->type = MIN(args->type, PROJ_DIRZ);
    args->gtype = MIN(args->gtype, GRAPH_DIRZ);
    args->update = !!args->update;
    args->perspective = !!args->perspective;
    args->render = !!args->render;
}
