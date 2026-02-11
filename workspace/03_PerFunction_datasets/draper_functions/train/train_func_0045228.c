nrf_snd_pkt_crc_encr(int size, uint8_t * pkt, uint32_t const key[4]){

    if(size > MAX_PKT)
        size=MAX_PKT;

    nrf_write_reg(R_CONFIG,
            R_CONFIG_PWR_UP|
            R_CONFIG_EN_CRC
            );


    uint16_t crc=crc16(pkt,size-2);
    pkt[size-2]=(crc >>8) & 0xff;
    pkt[size-1]=crc & 0xff;
    if(key !=NULL)
        xxtea_encode_words((uint32_t*)pkt,size/4,key);

    CS_LOW();
    xmit_spi(C_W_TX_PAYLOAD);
    sspSend(0,pkt,size);
    CS_HIGH();

    CE_HIGH();
    delayms(1);
    CE_LOW();

    return nrf_cmd_status(C_NOP);
}
