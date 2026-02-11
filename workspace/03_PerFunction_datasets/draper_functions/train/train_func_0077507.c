gx_make_clip_device_on_stack_if_needed(gx_device_clip * dev, const gx_clip_path *pcpath, gx_device *target, gs_fixed_rect *rect)
{

    if (rect->p.x < pcpath->outer_box.p.x)
        rect->p.x = pcpath->outer_box.p.x;
    if (rect->q.x > pcpath->outer_box.q.x)
        rect->q.x = pcpath->outer_box.q.x;
    if (rect->p.y < pcpath->outer_box.p.y)
        rect->p.y = pcpath->outer_box.p.y;
    if (rect->q.y > pcpath->outer_box.q.y)
        rect->q.y = pcpath->outer_box.q.y;
    if (pcpath->inner_box.p.x <= rect->p.x && pcpath->inner_box.p.y <= rect->p.y &&
        pcpath->inner_box.q.x >= rect->q.x && pcpath->inner_box.q.y >= rect->q.y)
    {

        return target;
    }
    else
    {

        if (rect->p.x >= rect->q.x || rect->p.y >= rect->q.y)
            return NULL;
    }
    gx_device_init_on_stack((gx_device *)dev, (const gx_device *)&gs_clip_device, target->memory);
    dev->list = *gx_cpath_list(pcpath);
    dev->translation.x = 0;
    dev->translation.y = 0;
    dev->HWResolution[0] = target->HWResolution[0];
    dev->HWResolution[1] = target->HWResolution[1];
    dev->sgr = target->sgr;
    dev->target = target;
    dev->graphics_type_tag = target->graphics_type_tag;

    (*dev_proc(dev, open_device)) ((gx_device *)dev);
    return (gx_device *)dev;
}
