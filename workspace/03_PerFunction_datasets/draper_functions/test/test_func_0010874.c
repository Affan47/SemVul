e1000_shift_in_mdi_bits(struct e1000_hw *hw)
{
    uint32_t ctrl;
    uint16_t data = 0;
    uint8_t i;


    ctrl = E1000_READ_REG(hw, CTRL);


    ctrl &= ~E1000_CTRL_MDIO_DIR;
    ctrl &= ~E1000_CTRL_MDIO;

    E1000_WRITE_REG(hw, CTRL, ctrl);
    E1000_WRITE_FLUSH(hw);


    e1000_raise_mdi_clk(hw, &ctrl);
    e1000_lower_mdi_clk(hw, &ctrl);

    for (data = 0, i = 0; i < 16; i++) {
        data = data << 1;
        e1000_raise_mdi_clk(hw, &ctrl);
        ctrl = E1000_READ_REG(hw, CTRL);

        if (ctrl & E1000_CTRL_MDIO)
            data |= 1;
        e1000_lower_mdi_clk(hw, &ctrl);
    }

    e1000_raise_mdi_clk(hw, &ctrl);
    e1000_lower_mdi_clk(hw, &ctrl);

    return data;
}
