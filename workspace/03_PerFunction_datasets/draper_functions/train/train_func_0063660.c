fs_emu_xml_shader_render(int texture, int texture_width,
        int texture_height, int input_width, int input_height,
        int output_width, int output_height, float x1, float y1,
        float x2, float y2, int render_textured_side, float alpha) {

    if (!fs_emu_xml_shader_is_enabled()) {
        return 0;
    }

    g_x1 = x1;
    g_x2 = x2;
    g_y1 = y1;
    g_y2 = y2;
    g_alpha = alpha;
    g_render_textured_side  = render_textured_side;

    fs_gl_blending(0);
    fs_gl_texturing(1);
    fs_gl_color4f(1.0, 1.0, 1.0, 1.0);


    g_cur_input_w = input_width;
    g_cur_input_h = input_height;


    g_cur_texture_w = texture_width;
    g_cur_texture_h = texture_height;


    g_final_output_w = output_width;
    g_final_output_h = output_height;


    g_requires_implicit_pass = 0;


    g_cur_texture = texture;
    debug_printf("\n\n\n\n\n");
    debug_printf("cur tex %d\n", g_cur_texture);

    g_orig_texture = g_cur_texture;
    g_orig_texture_w = g_cur_texture_w;
    g_orig_texture_h = g_cur_texture_h;
    g_orig_input_w = g_cur_input_w;
    g_orig_input_h = g_cur_input_h;

    debug_printf("final output: %d %d\n", g_final_output_w, g_final_output_h);
    debug_printf("       input: %d %d\n", g_cur_input_w, g_cur_input_h);
    debug_printf("     texture: %d %d\n", g_cur_texture_w, g_cur_texture_h);


    fs_list *link = g_active_shader->passes;
    int first = 1;
    while (link) {
        shader_pass *pass = link->data;
        render_pass(pass, first, link->next == NULL);
        first = 0;
        link = link->next;
    }


    if (g_requires_implicit_pass) {
        debug_printf("implicit pass, cur tex %d %d %d\n", g_cur_texture,
                g_cur_texture_w, g_cur_texture_h);


        float s2 = (float) g_cur_input_w / (float) g_cur_texture_w;
        float t2 = (float) g_cur_input_h / (float) g_cur_texture_h;
        fs_gl_bind_texture(g_cur_texture);
        render_quad(s2, 0.0, t2, 0, 1, 0);
    }
    CHECK_GL_ERROR();

    g_frame_count++;

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    CHECK_GL_ERROR();

    return 1;
}
