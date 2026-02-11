ReadGroup (GsfInput *in, Object *parent)
{
	guint16 code;
	Object *Group= parent->GetApplication ()->CreateObject ("group", parent);
	Group->Lock ();
	if (gsf_input_seek (in, 4, G_SEEK_CUR))
		return false;
	if (!(READINT16 (in,code)))
		return false;
	while (code) {
		if (code & kCDXTag_Object) {
			switch (code) {
			case kCDXObj_Fragment:
				if (!ReadMolecule (in, Group))
					return false;
				break;
			case kCDXObj_Text:
				if (!ReadText (in, Group))
					return false;
				break;
			default:
				if (!ReadGenericObject (in))
					return false;
			}
		} else {
			guint16 size;
			if ((size = ReadSize (in)) == 0xffff)
				return false;
			if (size && !gsf_input_read (in, size, (guint8*) buf))
				return false;
		}
		if (!(READINT16 (in,code)))
			return false;
	}
	Group->Lock (false);
	Group->OnLoaded ();
	parent->GetDocument ()->ObjectLoaded (Group);
	return true;
}
