__ecereNameSpace__ecere__com__Word_OnUnserialize(struct __ecereNameSpace__ecere__com__Class * _class, unsigned short * data, struct __ecereNameSpace__ecere__com__Instance * channel)
{
unsigned char bytes[2];

if(((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, unsigned char *  data, unsigned int numBytes))channel->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__com__IOChannel_ReadData])(channel, bytes, 2) == 2)
*data = (unsigned short)(((bytes)[0] << (unsigned char)8) | (bytes)[1]);
else
*data = (unsigned short)0;
}
