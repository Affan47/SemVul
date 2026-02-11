spotlight_read(Lib3dsLight *light, Lib3dsIo *io) {
    Lib3dsChunk c;
    uint16_t chunk;
    int i;

    lib3ds_chunk_read_start(&c, CHK_DL_SPOTLIGHT, io);

    light->spot_light = TRUE;
    for (i = 0; i < 3; ++i) {
        light->target[i] = lib3ds_io_read_float(io);
    }
    light->hotspot = lib3ds_io_read_float(io);
    light->falloff = lib3ds_io_read_float(io);
    lib3ds_chunk_read_tell(&c, io);

    while ((chunk = lib3ds_chunk_read_next(&c, io)) != 0) {
        switch (chunk) {
            case CHK_DL_SPOT_ROLL:
                light->roll = lib3ds_io_read_float(io);
                break;

            case CHK_DL_SHADOWED: {
                light->shadowed = TRUE;
                break;
            }

            case CHK_DL_LOCAL_SHADOW2: {
                light->shadow_bias = lib3ds_io_read_float(io);
                light->shadow_filter = lib3ds_io_read_float(io);
                light->shadow_size = lib3ds_io_read_intw(io);
                break;
            }

            case CHK_DL_SEE_CONE: {
                light->see_cone = TRUE;
                break;
            }

            case CHK_DL_SPOT_RECTANGULAR: {
                light->rectangular_spot = TRUE;
                break;
            }

            case CHK_DL_SPOT_ASPECT: {
                light->spot_aspect = lib3ds_io_read_float(io);
                break;
            }

            case CHK_DL_SPOT_PROJECTOR: {
                light->use_projector = TRUE;
                lib3ds_io_read_string(io, light->projector, 64);
                break;
            }

            case CHK_DL_SPOT_OVERSHOOT: {
                light->spot_overshoot = TRUE;
                break;
            }

            case CHK_DL_RAY_BIAS: {
                light->ray_bias = lib3ds_io_read_float(io);
                break;
            }

            case CHK_DL_RAYSHAD: {
                light->ray_shadows = TRUE;
                break;
            }

            default:
                lib3ds_chunk_unknown(chunk, io);
        }
    }

    lib3ds_chunk_read_end(&c, io);
}
