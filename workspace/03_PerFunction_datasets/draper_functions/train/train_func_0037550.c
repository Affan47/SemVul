isKatakana(uint16_t value) {
    return (value >= 0x30A1u && value <= 0x30FEu && value != 0x30FBu) ||
            (value >= 0xFF66u && value <= 0xFF9fu);
}
