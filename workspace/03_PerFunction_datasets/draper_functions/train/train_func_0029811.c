renderer_init_from_pointer(render_loader loader) {
    renderer = loader(&infon_api);

    if (renderer->version == RENDERER_API_VERSION)
        return 1;

    fprintf(stderr, "version mismatch between renderer and engine: renderer api %d != engine api %d\n",
                    renderer->version, RENDERER_API_VERSION);
    return 0;
}
