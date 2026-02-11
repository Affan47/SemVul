set_SEQUENCE_SEQUENCE(PT_sequence *THIS,bytestring * x){
			if(THIS->seq.data) free(THIS->seq.data);
			if(x){
				THIS->seq.data	= x->data;
				THIS->seq.size	= x->size;
			}else{
				THIS->seq.data	= 0;
				THIS->seq.size	= 0;
			}
		}
