CVectorGetElementptr(const CVectorHandle vectorhandle, void CVECTOR_FAR ** elementptr, const size_t index) {

        if ((vectorhandle==NULL)) { return CVECTOR_BAD_ARGUMENT; }

        if (index >= 0 && index < vectorhandle->size) {

            *elementptr = (void CVECTOR_FAR*)(((char *)(vectorhandle->array))+index*vectorhandle->elementsize);

            vectorhandle->flags |= CVECTOR_FLAGS_NO_RELOCATION;

            return 0;

        } else {

            return CVECTOR_NOT_FOUND;
        }

    }
