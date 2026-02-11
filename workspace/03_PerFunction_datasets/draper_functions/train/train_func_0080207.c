send(const char* buffer, long bytes2Send) {
		long bytesSent = 0;


		char bytes2SendBuf[50];
		int n=sprintf (bytes2SendBuf, "$%ld*", bytes2Send);
		write(this->client_socket, string(bytes2SendBuf).c_str(), n);
		do {
			int bytesSentThisTime = write(this->client_socket, buffer+bytesSent, bytes2Send-bytesSent);
			if (bytesSentThisTime < 0) {
				if (errno == EINTR) {
					cerr << "SEND: Interruption detected ..." << endl;
					continue;
				} else {
					cerr << "[aborted] Client>error in send..." << endl;
					exit(1);
				}
			} else {
				bytesSent += bytesSentThisTime;
			}
		} while (bytesSent < bytes2Send);

	}
