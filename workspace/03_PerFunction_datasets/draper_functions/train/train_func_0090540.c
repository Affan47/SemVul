msg_byte()
{

    if (moff >= 512) {
	get_block(++mblk);
	moff = 0;
    }


    return (decode(mbuf[moff++]));
}
