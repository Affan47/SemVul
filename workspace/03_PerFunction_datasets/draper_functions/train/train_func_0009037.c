signal_handler(int )
     {
          if (currentModel != NULL)
               currentModel->setMaximumIterations(0);
          return;
     }
