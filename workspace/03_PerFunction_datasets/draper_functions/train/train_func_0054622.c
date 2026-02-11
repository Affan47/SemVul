set_alignment (HAlignment halign, VAlignment valign) {
    if (halign != m_halign || valign != m_valign) {
        m_halign = halign;
        m_valign = valign;
        invalidate();
    }
}
