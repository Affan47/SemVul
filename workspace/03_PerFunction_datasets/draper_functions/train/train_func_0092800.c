EG_Update(struct _SLOT *slot)
{
	switch(slot->EG.state)
	{
		case ATTACK:
			slot->EG.volume+=slot->EG.AR;
			if(slot->EG.volume>=(0x3ff<<EG_SHIFT))
			{
				slot->EG.state=DECAY1;
				if(slot->EG.D1R>=(1024<<EG_SHIFT))
					slot->EG.state=DECAY2;
				slot->EG.volume=0x3ff<<EG_SHIFT;
			}
			if(slot->EG.EGHOLD)
				return 0x3ff<<(SHIFT-10);
			break;
		case DECAY1:
			slot->EG.volume-=slot->EG.D1R;
			if(slot->EG.volume>>(EG_SHIFT+5)>=slot->EG.DL)
				slot->EG.state=DECAY2;
			break;
		case DECAY2:
			if(D2R(slot)==0)
				return (slot->EG.volume>>EG_SHIFT)<<(SHIFT-10);
			slot->EG.volume-=slot->EG.D2R;
			if(slot->EG.volume<=0)
				slot->EG.volume=0;

			break;
		case RELEASE:
			slot->EG.volume-=slot->EG.RR;
			if(slot->EG.volume<=0)
			{
				SCSP_StopSlot(slot,0);
				slot->EG.volume=0;
				slot->EG.state=ATTACK;
			}
			break;
		default:
			return 1<<SHIFT;
	}
	return (slot->EG.volume>>EG_SHIFT)<<(SHIFT-10);
}
