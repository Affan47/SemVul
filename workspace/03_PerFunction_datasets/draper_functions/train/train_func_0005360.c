pars_2_message(_cmsg * cmsg)
{

	for (; TYP != _CEND; cmsg->p++) {
		switch (TYP) {
		case _CBYTE:
			byteTLcpy(cmsg->m + cmsg->l, OFF);
			cmsg->l++;
			break;
		case _CWORD:
			wordTLcpy(cmsg->m + cmsg->l, OFF);
			cmsg->l += 2;
			break;
		case _CDWORD:
			dwordTLcpy(cmsg->m + cmsg->l, OFF);
			cmsg->l += 4;
			break;
		case _CQWORD:
			qwordTLcpy (cmsg->m + cmsg->l, OFF);
			cmsg->l+=8;
			break;
		case _CSTRUCT:
			if (*(_cbyte **) OFF == 0) {
				*(cmsg->m + cmsg->l) = '\0';
				cmsg->l++;
			} else if (**(_cstruct *) OFF != 0xff) {
				structTLcpy(cmsg->m + cmsg->l, *(_cstruct *) OFF, 1 + **(_cstruct *) OFF);
				cmsg->l += 1 + **(_cstruct *) OFF;
			} else {
				_cword iw;
				_cstruct s = *(_cstruct *) OFF;
				structTLcpy(cmsg->m + cmsg->l, s, 3 + *(_cword *) (s + 1));
				wordTLcpy(&iw, (s + 1));
				cmsg->l += 3 + iw;
			}
			break;
		case _CMSTRUCT:

			if (*(_cmstruct *) OFF == CAPI_DEFAULT) {
				*(cmsg->m + cmsg->l) = '\0';
				cmsg->l++;
				jumpcstruct(cmsg);
			}

			else {
				unsigned _l = cmsg->l;
				_cword _ls;
				cmsg->l++;
				cmsg->p++;
				pars_2_message(cmsg);
				_ls = cmsg->l - _l - 1;
				if (_ls < 255)
					(cmsg->m + _l)[0] = (_cbyte) _ls;
				else {
					structTLcpyovl(cmsg->m + _l + 3, cmsg->m + _l + 1, _ls);
					(cmsg->m + _l)[0] = 0xff;
					wordTLcpy(cmsg->m + _l + 1, &_ls);
				}
			}
			break;
		}
	}
}
