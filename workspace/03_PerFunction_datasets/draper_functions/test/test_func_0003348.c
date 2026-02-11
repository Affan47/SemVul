Set()
        {
            cxxtools::xmlrpc::Service service;
            service.registerMethod("multiplyset", *this, &XmlRpcCallbackTest::multiplySet);
            _server->addService("/test", service);

            cxxtools::xmlrpc::HttpClient client(_loop, "", _port, "/test");
            cxxtools::RemoteProcedure<IntSet, IntSet, int> multiply(client, "multiplyset");
            connect( multiply.finished, *this, &XmlRpcCallbackTest::onSetFinished );

            IntSet myset;
            myset.insert(4);
            myset.insert(5);
            myset.insert(11);
            myset.insert(5);

            multiply.begin(myset, 2);

            _loop.run();
        }
