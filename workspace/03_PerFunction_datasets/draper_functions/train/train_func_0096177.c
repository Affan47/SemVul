svg_write_state(gx_device_svg *svg)
{
    char line[SVG_LINESIZE];


    if (!svg->dirty)
      return 0;


    if (svg->mark > 1) {
      svg_write(svg, "</g>\n");
      svg->mark--;
    }

    svg_write(svg, "<g ");
    if (svg->strokecolor != gx_no_color_index) {
        gs_sprintf(line, " stroke='#%06x'", (uint)(svg->strokecolor & 0xffffffL));
        svg_write(svg, line);
    } else {
        svg_write(svg, " stroke='none'");
    }
    if (svg->fillcolor != gx_no_color_index) {
        gs_sprintf(line, " fill='#%06x'", (uint)(svg->fillcolor & 0xffffffL));
        svg_write(svg, line);
    } else {
      svg_write(svg, " fill='none'");
    }
    if (svg->linewidth != 1.0) {
      gs_sprintf(line, " stroke-width='%lf'", svg->linewidth);
      svg_write(svg, line);
    }
    if (svg->linecap != SVG_DEFAULT_LINECAP) {
        switch (svg->linecap) {
          case gs_cap_round:
            svg_write(svg, " stroke-linecap='round'");
            break;
          case gs_cap_square:
            svg_write(svg, " stroke-linecap='square'");
            break;
          case gs_cap_butt:
          default:

            svg_write(svg, " stroke-linecap='butt'");
            break;
        }
    }
    if (svg->linejoin != SVG_DEFAULT_LINEJOIN) {
        switch (svg->linejoin) {
          case gs_join_round:
            svg_write(svg, " stroke-linejoin='round'");
            break;
          case gs_join_bevel:
            svg_write(svg, " stroke-linejoin='bevel'");
            break;
          case gs_join_miter:
          default:

            svg_write(svg, " stroke-linejoin='miter'");
            break;
        }
    }
    if (svg->miterlimit != SVG_DEFAULT_MITERLIMIT) {
        gs_sprintf(line, " stroke-miterlimit='%lf'", svg->miterlimit);
        svg_write(svg, line);
    }
    svg_write(svg, ">\n");
    svg->mark++;

    svg->dirty = 0;
    return 0;
}
