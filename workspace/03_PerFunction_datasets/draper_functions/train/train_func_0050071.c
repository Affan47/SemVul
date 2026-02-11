__ecereNameSpace__ecere__com__Int64_OnSerialize(struct __ecereNameSpace__ecere__com__Class * _class, long long * data, struct __ecereNameSpace__ecere__com__Instance * channel)
{
unsigned char bytes[8];

(bytes)[0] = (unsigned char)(((*data) >> 56) & 0xFF);
(bytes)[1] = (unsigned char)(((*data) >> 48) & 0xFF);
(bytes)[2] = (unsigned char)(((*data) >> 40) & 0xFF);
(bytes)[3] = (unsigned char)(((*data) >> 32) & 0xFF);
(bytes)[4] = (unsigned char)(((*data) >> 24) & 0xFF);
(bytes)[5] = (unsigned char)(((*data) >> 16) & 0xFF);
(bytes)[6] = (unsigned char)(((*data) >> 8) & 0xFF);
(bytes)[7] = (unsigned char)((*data) & 0xFF);
;
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, unsigned char *  data, unsigned int numBytes))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = channel;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__IOChannel->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__IOChannel_WriteData])(channel, bytes, 8);
}
