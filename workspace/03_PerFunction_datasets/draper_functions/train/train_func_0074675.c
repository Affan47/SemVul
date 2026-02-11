finish_vencrypt_auth(rfbClientPtr client, int subtype) {

	if (subtype == rfbVencryptTlsNone || subtype == rfbVencryptX509None) {
		return finish_auth(client, "None");
	} else if (subtype == rfbVencryptTlsVnc || subtype == rfbVencryptX509Vnc) {
		return finish_auth(client, "Vnc");
	} else if (subtype == rfbVencryptTlsPlain || subtype == rfbVencryptX509Plain) {
		return finish_auth(client, "Plain");
	} else {
		rfbLog("finish_vencrypt_auth: unknown sub-type: %d\n", subtype);
		return 0;
	}
}
