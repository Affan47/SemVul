rftransfer_receive(uint8_t *buffer, uint16_t maxlen, uint16_t timeout)
{
    uint8_t buf[MAXPACKET];
    uint8_t state = 0;
    uint16_t pos = 0, seq = 0, size = 0, rand = 0, crc = 0;
    int n,i;
    unsigned int currentTick = systickGetTicks();
    unsigned int startTick = currentTick;

    while(systickGetTicks() < (startTick+timeout) ){
        n = nrf_rcv_pkt_time(1000, MAXPACKET, buf);
        switch(state){
            case 0:
                if( n == 32 && buf[0] == 'L' ){
                    size = (buf[1] << 8) | buf[2];
                    rand =  (buf[3] << 8) | buf[4];
                    seq = 0;
                    pos = 0;
                    if( size <= maxlen ){


                        state = 1;
                    }
                }
            break;
            case 1:
                if( n == 32 && buf[0] == 'D' && ((buf[3]<<8)|buf[4])==rand ){

                    if( seq == ((buf[1]<<8)|buf[2]) ){

                            for(i=5; i<n-2 && pos<size; i++,pos++){
                                buffer[pos] = buf[i];
                            }
                            seq++;
                    }
                }
                if( pos == size ){

                    crc = crc16(buffer, size);
                    state = 2;
                }
            break;
            case 2:
                if( n == 32 && buf[0] == 'C' && ((buf[3]<<8)|buf[4])==rand){

                    if( crc == ((buf[1]<<8)|buf[2]) ){

                        return size;
                    }else{

                        return -1;
                    }
                }
            break;
        };
    }

    return -2;
}
