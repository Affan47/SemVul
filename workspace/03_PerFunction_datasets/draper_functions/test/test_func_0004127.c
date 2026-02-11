client_tick(uint32 tick)
{
    info_buffer_tick();
    inventory_tick();
    mapdata_animation();


    if (have_new_image && !(tick % 5)) {
        if (cpl.container)
            cpl.container->inv_updated=1;
        cpl.ob->inv_updated=1;

        have_new_image=0;
        draw_map(1);
        draw_lists();
    } else {
        draw_map(0);
    }
}
