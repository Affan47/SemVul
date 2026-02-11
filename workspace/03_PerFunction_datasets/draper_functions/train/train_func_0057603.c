__ecereNameSpace__ecere__com__Byte_OnUnserialize(struct __ecereNameSpace__ecere__com__Class * _class, unsigned char * data, struct __ecereNameSpace__ecere__com__Instance * channel)
{
if(((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, unsigned char *  data, unsigned int numBytes))channel->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__com__IOChannel_ReadData])(channel, data, 1) != 1)
*data = (unsigned char)0;
}
