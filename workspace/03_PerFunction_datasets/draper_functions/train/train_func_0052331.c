e1000_read_ich8_data(struct e1000_hw *hw, uint32_t index,
                     uint32_t size, uint16_t* data)
{
    union ich8_hws_flash_status hsfsts;
    union ich8_hws_flash_ctrl hsflctl;
    uint32_t flash_linear_address;
    uint32_t flash_data = 0;
    int32_t error = -E1000_ERR_EEPROM;
    int32_t count = 0;

    DEBUGFUNC("e1000_read_ich8_data");

    if (size < 1  || size > 2 || data == 0x0 ||
        index > ICH_FLASH_LINEAR_ADDR_MASK)
        return error;

    flash_linear_address = (ICH_FLASH_LINEAR_ADDR_MASK & index) +
                           hw->flash_base_addr;

    do {
        udelay(1);

        error = e1000_ich8_cycle_init(hw);
        if (error != E1000_SUCCESS)
            break;

        hsflctl.regval = E1000_READ_ICH_FLASH_REG16(hw, ICH_FLASH_HSFCTL);

        hsflctl.hsf_ctrl.fldbcount = size - 1;
        hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_READ;
        E1000_WRITE_ICH_FLASH_REG16(hw, ICH_FLASH_HSFCTL, hsflctl.regval);


        E1000_WRITE_ICH_FLASH_REG(hw, ICH_FLASH_FADDR, flash_linear_address);

        error = e1000_ich8_flash_cycle(hw, ICH_FLASH_COMMAND_TIMEOUT);


        if (error == E1000_SUCCESS) {
            flash_data = E1000_READ_ICH_FLASH_REG(hw, ICH_FLASH_FDATA0);
            if (size == 1) {
                *data = (uint8_t)(flash_data & 0x000000FF);
            } else if (size == 2) {
                *data = (uint16_t)(flash_data & 0x0000FFFF);
            }
            break;
        } else {


            hsfsts.regval = E1000_READ_ICH_FLASH_REG16(hw, ICH_FLASH_HSFSTS);
            if (hsfsts.hsf_status.flcerr == 1) {

                continue;
            } else if (hsfsts.hsf_status.flcdone == 0) {
                DEBUGOUT("Timeout error - flash cycle did not complete.");
                break;
            }
        }
    } while (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

    return error;
}
