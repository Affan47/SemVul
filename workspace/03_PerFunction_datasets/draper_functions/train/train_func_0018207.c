e1000_erase_ich8_4k_segment(struct e1000_hw *hw, uint32_t bank)
{
    union ich8_hws_flash_status hsfsts;
    union ich8_hws_flash_ctrl hsflctl;
    uint32_t flash_linear_address;
    int32_t  count = 0;
    int32_t  error = E1000_ERR_EEPROM;
    int32_t  iteration;
    int32_t  sub_sector_size = 0;
    int32_t  bank_size;
    int32_t  j = 0;
    int32_t  error_flag = 0;

    hsfsts.regval = E1000_READ_ICH_FLASH_REG16(hw, ICH_FLASH_HSFSTS);


    if (hsfsts.hsf_status.berasesz == 0x0) {

        sub_sector_size = ICH_FLASH_SEG_SIZE_256;
        bank_size = ICH_FLASH_SECTOR_SIZE;
        iteration = ICH_FLASH_SECTOR_SIZE / ICH_FLASH_SEG_SIZE_256;
    } else if (hsfsts.hsf_status.berasesz == 0x1) {
        bank_size = ICH_FLASH_SEG_SIZE_4K;
        iteration = 1;
    } else if (hsfsts.hsf_status.berasesz == 0x3) {
        bank_size = ICH_FLASH_SEG_SIZE_64K;
        iteration = 1;
    } else {
        return error;
    }

    for (j = 0; j < iteration ; j++) {
        do {
            count++;

            error = e1000_ich8_cycle_init(hw);
            if (error != E1000_SUCCESS) {
                error_flag = 1;
                break;
            }


            hsflctl.regval = E1000_READ_ICH_FLASH_REG16(hw, ICH_FLASH_HSFCTL);
            hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_ERASE;
            E1000_WRITE_ICH_FLASH_REG16(hw, ICH_FLASH_HSFCTL, hsflctl.regval);


            flash_linear_address = bank * bank_size + j * sub_sector_size;
            flash_linear_address += hw->flash_base_addr;
            flash_linear_address &= ICH_FLASH_LINEAR_ADDR_MASK;

            E1000_WRITE_ICH_FLASH_REG(hw, ICH_FLASH_FADDR, flash_linear_address);

            error = e1000_ich8_flash_cycle(hw, ICH_FLASH_ERASE_TIMEOUT);


            if (error == E1000_SUCCESS) {
                break;
            } else {
                hsfsts.regval = E1000_READ_ICH_FLASH_REG16(hw, ICH_FLASH_HSFSTS);
                if (hsfsts.hsf_status.flcerr == 1) {

                    continue;
                } else if (hsfsts.hsf_status.flcdone == 0) {
                    error_flag = 1;
                    break;
                }
            }
        } while ((count < ICH_FLASH_CYCLE_REPEAT_COUNT) && !error_flag);
        if (error_flag == 1)
            break;
    }
    if (error_flag != 1)
        error = E1000_SUCCESS;
    return error;
}
