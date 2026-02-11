__ecereMethod___ecereNameSpace__ecere__net__FileServerConnection_SendSizePacket(struct __ecereNameSpace__ecere__com__Instance * this, int handle)
{
struct __ecereNameSpace__ecere__net__FileServerConnection * __ecerePointer___ecereNameSpace__ecere__net__FileServerConnection = (struct __ecereNameSpace__ecere__net__FileServerConnection *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__net__FileServerConnection->offset) : 0);
struct __ecereNameSpace__ecere__net__SizePacket packet =
{

{
(unsigned char)(((3) >> 24) & 0xFF), (unsigned char)(((3) >> 16) & 0xFF), (unsigned char)(((3) >> 8) & 0xFF), (unsigned char)((3) & 0xFF)
},
{
(unsigned char)(((__ecereClass___ecereNameSpace__ecere__net__SizePacket->structSize) >> 24) & 0xFF), (unsigned char)(((__ecereClass___ecereNameSpace__ecere__net__SizePacket->structSize) >> 16) & 0xFF), (unsigned char)(((__ecereClass___ecereNameSpace__ecere__net__SizePacket->structSize) >> 8) & 0xFF), (unsigned char)((__ecereClass___ecereNameSpace__ecere__net__SizePacket->structSize) & 0xFF)
},
{
(unsigned char)(((handle) >> 24) & 0xFF), (unsigned char)(((handle) >> 16) & 0xFF), (unsigned char)(((handle) >> 8) & 0xFF), (unsigned char)((handle) & 0xFF)
}
};

__ecereMethod___ecereNameSpace__ecere__net__Socket_Send(this, &packet, (unsigned int)((packet.size[0] << (unsigned char)24) | (packet.size[1] << (unsigned char)16) | (packet.size[2] << (unsigned char)8) | packet.size[3]));
}
