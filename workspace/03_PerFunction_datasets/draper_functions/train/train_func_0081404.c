gsp_parse_state(void *gsvg_state, void *gsp_source) {
        Graphics_svg_state *svg_state;
        Graphics_sprite_source *sprite_source;
        Graphics_sprite_state *sprite_state;

        svg_state = (Graphics_svg_state *) gsvg_state;
        sprite_source = (Graphics_sprite_source *) gsp_source;
        sprite_state = new_sprite_state();

				sprite_state_set_state(sprite_state, svg_state->state);
				GDEBUG("sprite_state->state: %d", sprite_state->state);

				sprite_state_set_fpp(sprite_state, svg_state->fpp);
				GDEBUG("sprite_state->fpp: %d", sprite_state->fpp);

				GDEBUG("Parse all pics in the state");
        list_foreach(svg_state->svg, gsp_parse_pic, sprite_state);

				GDEBUG("Appending sprite_state.");
				sprite_source_add_state(sprite_source, sprite_state);

        return TRUE;
}
