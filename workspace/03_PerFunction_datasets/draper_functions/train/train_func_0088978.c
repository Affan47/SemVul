mesh_sanity(uint8_t * pkt){
    if(MO_TYPE(pkt)>0x7f || MO_TYPE(pkt)<0x20)
        return 1;
    if(MO_TYPE(pkt)=='T' && MO_BODY(pkt)[5])
           return 3;
    if(MO_TYPE(pkt)>='A' && MO_TYPE(pkt)<='Z'){
        if(MO_TIME(pkt)>1325379600)
            return 1;
        if(MO_TIME(pkt)<1324602000)
            return 1;
    }else if(MO_TYPE(pkt)>='a' && MO_TYPE(pkt)<='z'){
        if(MO_TIME(pkt)>16777216)
            return 1;
        if(MO_TIME(pkt)<0)
            return 1;
    };
    if(MO_TYPE(pkt)!='A' &&
       MO_TYPE(pkt)!='a' &&
       MO_TYPE(pkt)!='B' &&
       MO_TYPE(pkt)!='E' &&
       MO_TYPE(pkt)!='F' &&
       MO_TYPE(pkt)!='G' &&
       MO_TYPE(pkt)!='T'
            ){
        return 2;
    };
    return 0;
}
