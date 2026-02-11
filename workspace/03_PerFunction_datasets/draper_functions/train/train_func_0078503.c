updateRecycleDetails(GameLogic::Country* country, bool recyclePhase, int nbAvailArmies)
{
  kDebug() << (void*)country << recyclePhase << nbAvailArmies;
  this->show();
  if (btValidWidget == 0)
  {
    if (country == 0)
    {
      return;
    }
    displayRecycleDetails(country->owner(),nbAvailArmies);
  }

  if (recyclePhase)
  {
    rightContents.at(0)->setText(i18n("<u><b>Change some<br>placements?</b></u> "));
    flag1->hide();
    rightContents.at(1)->setText(QString());
    rightContents.at(2)->setText(QString());
    rightContents.at(3)->setText(QString());


    if (!game->automaton()->allLocalPlayersComputer())
    {
      btRecycleWidget->show();
    }
    btValidWidget->hide();
  }
  else
  {
    rightContents.at(1)->setText(i18np("1 army to place", "%1 armies to place", nbAvailArmies));
    rightContents.at(2)->setText("<b>"+i18n(country->name().toUtf8().data())+"</b>");
    rightContents.at(3)->setText(i18n("<b>Armies:</b> %1", country->nbArmies()));
    if (nbAvailArmies > 0)
    {
      btValidWidget->hide();
    }
    else
    {
      if (!game->currentPlayer()->isVirtual() && !game->currentPlayer()->isAI())
      {
        btValidWidget->show();
      }
    }
  }
  kDebug() << "before update and repaint";
  mainLayout->update();
  repaint();

}
