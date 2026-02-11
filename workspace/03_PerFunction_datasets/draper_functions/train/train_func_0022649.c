Main ()
        {
          if (registering) {
            if (presentity && !presentity->IsOpen ())
              presentity->Open ();
            manager.Register (account);
          } else {
            manager.Unregister (account);

            if (presentity && presentity->IsOpen ())
              presentity->Close ();

          }
        }
