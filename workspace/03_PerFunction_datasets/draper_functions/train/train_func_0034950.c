_enable_button(GRAPHICS_CONTROLLER *gc, uint32_t button_id, unsigned enable)
{
    PG_DISPLAY_SET *s          = gc->igs;
    BD_IG_PAGE     *page       = NULL;
    BD_IG_BUTTON   *button     = NULL;
    unsigned        page_id    = bd_psr_read(gc->regs, PSR_MENU_PAGE_ID);
    unsigned        cur_btn_id = bd_psr_read(gc->regs, PSR_SELECTED_BUTTON_ID);
    unsigned        bog_idx    = 0;

    GC_TRACE("_enable_button(#%d, %s)\n", button_id, enable ? "enable" : "disable");

    page = _find_page(&s->ics->interactive_composition, page_id);
    if (!page) {
        GC_TRACE("_enable_button(): unknown page #%d (have %d pages)\n",
              page_id, s->ics->interactive_composition.num_pages);
        return;
    }


    button = _find_button_page(page, button_id, &bog_idx);
    if (!button) {
        GC_TRACE("_enable_button(): unknown button #%d (page #%d)\n", button_id, page_id);
        return;
    }

    if (enable) {
        if (gc->bog_data[bog_idx].enabled_button == cur_btn_id) {

            bd_psr_write(gc->regs, PSR_SELECTED_BUTTON_ID, 0x10000|button_id);
        }
        gc->bog_data[bog_idx].enabled_button = button_id;
        gc->bog_data[bog_idx].animate_indx = 0;

    } else {
        if (gc->bog_data[bog_idx].enabled_button == button_id) {
            gc->bog_data[bog_idx].enabled_button = 0xffff;
        }

        if (cur_btn_id == button_id) {
            bd_psr_write(gc->regs, PSR_SELECTED_BUTTON_ID, 0xffff);
        }
    }
}
