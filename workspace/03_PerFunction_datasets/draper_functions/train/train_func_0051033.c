newEmail( int player )
      {
          gamemap->player[player].email = editString2( "Mail Address for " + gamemap->player[player].getName(), gamemap->player[player].email);
      }
