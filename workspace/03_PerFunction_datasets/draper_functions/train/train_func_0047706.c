e1000_read_ich8_byte(struct e1000_hw *hw, uint32_t index, uint8_t* data)
{
    int32_t status = E1000_SUCCESS;
    uint16_t word = 0;

    status = e1000_read_ich8_data(hw, index, 1, &word);
    if (status == E1000_SUCCESS) {
        *data = (uint8_t)word;
    }

    return status;
}
