Invoke()
{
    if(clamp)
        glCombinerParameteriNV(GL_COLOR_SUM_CLAMP_NV, GL_TRUE);
    else
        glCombinerParameteriNV(GL_COLOR_SUM_CLAMP_NV, GL_FALSE);

    glFinalCombinerInputNV(
        GL_VARIABLE_A_NV,
        rgb.a.reg.bits.name,
        rgb.a.map,
        MAP_CHANNEL(rgb.a.reg.bits.channel));

    glFinalCombinerInputNV(
        GL_VARIABLE_B_NV,
        rgb.b.reg.bits.name,
        rgb.b.map,
        MAP_CHANNEL(rgb.b.reg.bits.channel));

    glFinalCombinerInputNV(
        GL_VARIABLE_C_NV,
        rgb.c.reg.bits.name,
        rgb.c.map,
        MAP_CHANNEL(rgb.c.reg.bits.channel));

    glFinalCombinerInputNV(
        GL_VARIABLE_D_NV,
        rgb.d.reg.bits.name,
        rgb.d.map,
        MAP_CHANNEL(rgb.d.reg.bits.channel));

    glFinalCombinerInputNV(
        GL_VARIABLE_E_NV,
        product.e.reg.bits.name,
        product.e.map,
        MAP_CHANNEL(product.e.reg.bits.channel));

    glFinalCombinerInputNV(
        GL_VARIABLE_F_NV,
        product.f.reg.bits.name,
        product.f.map,
        MAP_CHANNEL(product.f.reg.bits.channel));

    glFinalCombinerInputNV(
        GL_VARIABLE_G_NV,
        alpha.g.reg.bits.name,
        alpha.g.map,
        MAP_CHANNEL(alpha.g.reg.bits.channel));
}
