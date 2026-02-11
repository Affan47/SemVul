finish(void* signature_) {
        if (!finished) {
            if (message_length[0] + stored_size < message_length[0])
                message_length[1]++;
            message_length[0] += stored_size;

            int pad = md5::BLOCK_SIZE - (sizeof(unsigned int) * 2) - stored_size;
            if (pad <= 0)
                pad += md5::BLOCK_SIZE;


            if (pad > 0) {
                stored[stored_size] = 0x80;
                if (pad > 1)
                    memset(stored + stored_size + 1, 0, pad - 1);
                stored_size += pad;
            }


            unsigned int size_low = ((message_length[0] & 0x1FFFFFFF) << 3);
            memcpy(stored + stored_size, &size_low, sizeof(unsigned int));
            stored_size += sizeof(unsigned int);


            unsigned int size_high = (message_length[1] << 3) | ((message_length[0] & 0xE0000000) >> 29);
            memcpy(stored + stored_size, &size_high, sizeof(unsigned int));
            stored_size += sizeof(unsigned int);


            process_block(stored);
            if (stored_size > md5::BLOCK_SIZE)
                process_block(stored + md5::BLOCK_SIZE);


            get_result(static_cast<void*>(signature));


            sig_to_string(signature, str, MD5_STRING_SIZE);

            if (signature_ != NULL) {
                memcpy(signature_, static_cast<void*>(signature), MD5_SIZE);
            }

            finished = true;
        } else {

        }
    }
